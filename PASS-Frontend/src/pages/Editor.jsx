import { useSimulinkEditor } from '../hooks/useSimulinkEditor';

import Toolbar              from '../components/Toolbar/Toolbar';
import BlockLibraryPanel    from '../components/Block/BlockLibraryPanel';
import PropertiesPanel      from '../components/Block/PropertiesPanel';
import SimulinkCanvas       from '../components/Canvas/SimulinkCanvas';
import ScopePanel           from '../components/Scope/ScopePanel';
import SimulationControls   from '../components/Scope/SimulationControls';

import './Editor.css';

export default function Editor() {
  const editorState = useSimulinkEditor();
  if (typeof window !== 'undefined') {
    window.simulinkEditor = editorState;
  }

  const {
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
  } = editorState;

  return (
    <div className="editor">
      {}
      <Toolbar
        simStatus={simStatus}
        onRun={runSimulation}
        onSave={saveProject}
        onLoad={loadProject}
        onClear={clearAll}
      />

      {}
      <div className="editor__workspace">
        {}
        <BlockLibraryPanel />

        {}
        <div className="editor__center">
          <SimulinkCanvas
            blocks={blocks}
            connections={connections}
            selectedBlockId={selectedBlockId}
            onSelect={selectBlock}
            onAddBlock={addBlock}
            onMoveBlock={moveBlock}
            onDeleteBlock={deleteBlock}
            onConnectPorts={connectPorts}
            onDeleteConnection={deleteConnection}
          />

          {}
          <ScopePanel
            scopeData={scopeData}
            simStatus={simStatus}
            settings={settings}
          />

          {}
          <SimulationControls
            settings={settings}
            onSettingsChange={updateSettings}
            onRun={runSimulation}
            simStatus={simStatus}
            simError={simError}
          />
        </div>

        {}
        <PropertiesPanel
          block={selectedBlock}
          onParamChange={updateBlockParams}
          onIdChange={updateBlockId}
          onDelete={deleteBlock}
        />
      </div>

      {}
      {notification && (
        <div
          className={`editor__toast editor__toast--${notification.type}`}
          role="status"
          aria-live="polite"
        >
          {notification.msg}
        </div>
      )}
    </div>
  );
}
