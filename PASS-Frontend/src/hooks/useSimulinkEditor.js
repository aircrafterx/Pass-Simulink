

import { useState, useCallback, useRef } from 'react';
import { BLOCK_TYPES } from '../models/blockTypes';
import * as api from '../services/simulationApi';

let _blockCounter = 1;
function nextId(type) {
  return `${type}_${_blockCounter++}`;
}

const DEFAULT_SETTINGS = {
  startTime: 0.0,
  endTime:   10.0,
  stepSize:  0.1,
};

export function useSimulinkEditor() {
  const [blocks,          setBlocks]          = useState([]);
  const [connections,     setConnections]     = useState([]);
  const [selectedBlockId, setSelectedBlockId] = useState(null);
  const [settings,        setSettings]        = useState(DEFAULT_SETTINGS);
  const [scopeData,       setScopeData]       = useState({});
  const [simStatus,       setSimStatus]       = useState('idle');
  const [simError,        setSimError]        = useState(null);
  const [notification,    setNotification]    = useState(null);

  const notifTimerRef = useRef(null);
  const simTimerRef   = useRef(null);


  const notify = useCallback((msg, type = 'info') => {
    if (notifTimerRef.current) clearTimeout(notifTimerRef.current);
    setNotification({ msg, type });
    notifTimerRef.current = setTimeout(() => setNotification(null), 3500);
  }, []);


  const addBlock = useCallback((type, x = 200, y = 200) => {
    const def = BLOCK_TYPES[type];
    if (!def) return;
    const id = nextId(type);
    setBlocks(prev => [...prev, {
      id,
      type,
      x,
      y,
      params: { ...def.defaultParams },
    }]);
    setSelectedBlockId(id);
    return id;
  }, []);

  const moveBlock = useCallback((id, x, y) => {
    setBlocks(prev => prev.map(b => b.id === id ? { ...b, x, y } : b));
  }, []);

  const deleteBlock = useCallback((id) => {
    setBlocks(prev => prev.filter(b => b.id !== id));
    setConnections(prev => prev.filter(c => c.from !== id && c.to !== id));
    setSelectedBlockId(sid => sid === id ? null : sid);
  }, []);

  const updateBlockParams = useCallback((id, params) => {
    setBlocks(prev => prev.map(b => b.id === id ? { ...b, params: { ...b.params, ...params } } : b));
  }, []);

  const updateBlockId = useCallback((oldId, newId) => {
    if (!newId.trim() || blocks.find(b => b.id === newId)) return false;
    setBlocks(prev => prev.map(b => b.id === oldId ? { ...b, id: newId } : b));
    setConnections(prev => prev.map(c => ({
      ...c,
      from: c.from === oldId ? newId : c.from,
      to:   c.to   === oldId ? newId : c.to,
    })));
    setSelectedBlockId(sid => sid === oldId ? newId : sid);
    return true;
  }, [blocks]);

  const selectBlock = useCallback((id) => setSelectedBlockId(id), []);

  const selectedBlock = blocks.find(b => b.id === selectedBlockId) ?? null;


  const connectPorts = useCallback((from, fromPort, to, toPort) => {

    const dup = connections.find(
      c => c.to === to && c.toPort === toPort
    );
    if (dup) return false;
    if (from === to) return false;
    setConnections(prev => [...prev, { from, fromPort, to, toPort }]);
    return true;
  }, [connections]);

  const deleteConnection = useCallback((from, fromPort, to, toPort) => {
    setConnections(prev => prev.filter(
      c => !(c.from === from && c.fromPort === fromPort &&
             c.to   === to   && c.toPort   === toPort)
    ));
  }, []);


  const updateSettings = useCallback((patch) => {
    setSettings(prev => ({ ...prev, ...patch }));
  }, []);


  const buildProject = useCallback(() => ({
    blocks: blocks.map(b => ({
      id:     b.id,
      type:   b.type,
      x:      b.x,
      y:      b.y,
      params: b.params,
    })),
    connections: connections.map(c => ({
      from:     c.from,
      fromPort: c.fromPort,
      to:       c.to,
      toPort:   c.toPort,
    })),
    settings: { ...settings },
  }), [blocks, connections, settings]);


  const runSimulation = useCallback(async () => {
    if (simTimerRef.current) clearInterval(simTimerRef.current);
    setSimStatus('running');
    setSimError(null);
    setScopeData({});
    try {
      const project = buildProject();
      const result  = await api.runSimulation(project);
      const scopes = result.scopes ?? {};
      const scopeIds = Object.keys(scopes);

      if (scopeIds.length === 0) {
        setScopeData({});
        setSimStatus('done');
        notify('Simulation complete!', 'success');
        return;
      }

      let maxLen = 0;
      for (const id of scopeIds) {
        maxLen = Math.max(maxLen, scopes[id].length);
      }

      if (maxLen === 0) {
        setScopeData({});
        setSimStatus('done');
        notify('Simulation complete!', 'success');
        return;
      }

      let currentIndex = 0;
      const intervalMs = Math.max(8, Math.min(40, 1500 / maxLen));

      simTimerRef.current = setInterval(() => {
        currentIndex++;
        setScopeData(() => {
          const nextData = {};
          for (const id of scopeIds) {
            nextData[id] = scopes[id].slice(0, currentIndex);
          }
          return nextData;
        });

        if (currentIndex >= maxLen) {
          clearInterval(simTimerRef.current);
          simTimerRef.current = null;
          setSimStatus('done');
          notify('Simulation complete!', 'success');
        }
      }, intervalMs);
    } catch (err) {
      setSimError(err.message);
      setSimStatus('error');
      notify(`Simulation error: ${err.message}`, 'error');
    }
  }, [buildProject, notify]);


  const saveProject = useCallback(async () => {
    try {
      await api.saveProject(buildProject());
      notify('Project saved.', 'success');
    } catch (err) {
      notify(`Save failed: ${err.message}`, 'error');
    }
  }, [buildProject, notify]);

  const loadProject = useCallback(async () => {
    if (simTimerRef.current) {
      clearInterval(simTimerRef.current);
      simTimerRef.current = null;
    }
    try {
      const project = await api.loadProject();

      _blockCounter = 1;
      setBlocks(
        (project.blocks ?? []).map(b => ({
          id:     b.id,
          type:   b.type,
          x:      b.x ?? 100,
          y:      b.y ?? 100,
          params: b.params ?? {},
        }))
      );
      setConnections(project.connections ?? []);
      if (project.settings) setSettings(project.settings);
      setSelectedBlockId(null);
      setScopeData({});
      setSimStatus('idle');
      notify('Project loaded.', 'success');
    } catch (err) {
      notify(`Load failed: ${err.message}`, 'error');
    }
  }, [notify]);


  const clearAll = useCallback(() => {
    if (simTimerRef.current) {
      clearInterval(simTimerRef.current);
      simTimerRef.current = null;
    }
    setBlocks([]);
    setConnections([]);
    setSelectedBlockId(null);
    setScopeData({});
    setSimStatus('idle');
    setSimError(null);
    _blockCounter = 1;
  }, []);

  return {

    blocks,
    connections,
    selectedBlockId,
    selectedBlock,
    settings,
    scopeData,
    simStatus,
    simError,
    notification,


    addBlock,
    moveBlock,
    deleteBlock,
    updateBlockParams,
    updateBlockId,
    selectBlock,


    connectPorts,
    deleteConnection,


    updateSettings,


    runSimulation,
    saveProject,
    loadProject,
    clearAll,
  };
}
