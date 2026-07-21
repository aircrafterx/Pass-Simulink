import { useRef, useState, useCallback } from 'react';
import BlockNode, { BLOCK_W, BLOCK_H } from '../Block/BlockNode';
import ConnectionLayer from '../Connection/ConnectionLayer';
import { BLOCK_TYPES } from '../../models/blockTypes';
import './SimulinkCanvas.css';


export default function SimulinkCanvas({
  blocks,
  connections,
  selectedBlockId,
  onSelect,
  onAddBlock,
  onMoveBlock,
  onDeleteBlock,
  onConnectPorts,
  onDeleteConnection,
}) {
  const svgRef = useRef(null);


  const [pendingPort, setPendingPort] = useState(null);
  const [mousePos,    setMousePos]    = useState(null);


  const svgPoint = useCallback((clientX, clientY) => {
    if (!svgRef.current) return { x: clientX, y: clientY };
    const rect = svgRef.current.getBoundingClientRect();
    return {
      x: clientX - rect.left,
      y: clientY - rect.top,
    };
  }, []);


  const onDragOver = (e) => {
    e.preventDefault();
    e.dataTransfer.dropEffect = 'copy';
  };

  const onDrop = (e) => {
    e.preventDefault();
    const type = e.dataTransfer.getData('blockType');
    if (!type || !BLOCK_TYPES[type]) return;
    const pos = svgPoint(e.clientX, e.clientY);

    onAddBlock(type, pos.x - BLOCK_W / 2, pos.y - BLOCK_H / 2);
  };


  const onMouseMove = (e) => {
    if (!pendingPort) return;
    setMousePos(svgPoint(e.clientX, e.clientY));
  };


  const onBgClick = () => {
    if (pendingPort) {
      setPendingPort(null);
      setMousePos(null);
    } else {
      onSelect(null);
    }
  };


  const handlePortDown = useCallback((blockId, isInput, portIndex) => {
    if (!pendingPort) {
      setPendingPort({ blockId, isInput, portIndex });
    }
  }, [pendingPort]);


  const handlePortUp = useCallback((blockId, isInput, portIndex) => {
    if (!pendingPort) return;

    const from = pendingPort;
    const to   = { blockId, isInput, portIndex };


    if (from.isInput === to.isInput) {
      if (from.blockId === to.blockId && from.portIndex === to.portIndex) {

        return;
      }

      setPendingPort({ blockId, isInput, portIndex });
      return;
    }

    const [output, input] = from.isInput
      ? [to, from]
      : [from, to];

    onConnectPorts(output.blockId, output.portIndex, input.blockId, input.portIndex);
    setPendingPort(null);
    setMousePos(null);
  }, [pendingPort, onConnectPorts]);

  const isEmpty = blocks.length === 0;

  return (
    <div
      className="canvas-wrap"
      onDragOver={onDragOver}
      onDrop={onDrop}
    >
      {isEmpty && (
        <div className="canvas-empty-hint">
          <div className="canvas-empty-hint__icon">⬡</div>
          <div className="canvas-empty-hint__text">Canvas is empty</div>
          <div className="canvas-empty-hint__sub">
            Drag blocks from the library panel on the left
          </div>
        </div>
      )}

      <svg
        ref={svgRef}
        id="simulink-canvas-svg"
        className={`canvas-svg${pendingPort ? ' connecting' : ''}`}
        onMouseMove={onMouseMove}
        onClick={onBgClick}
        onMouseLeave={() => { if (pendingPort) setMousePos(null); }}
      >
        {}
        <defs>
          <pattern id="grid" width={32} height={32} patternUnits="userSpaceOnUse">
            <circle cx={16} cy={16} r={0.8} fill="rgba(255,255,255,0.04)" />
          </pattern>
        </defs>
        <rect width="100%" height="100%" fill="url(#grid)" style={{ pointerEvents: 'none' }} />

        {}
        <ConnectionLayer
          blocks={blocks}
          connections={connections}
          pendingPort={pendingPort}
          mousePos={mousePos}
          onDeleteConnection={onDeleteConnection}
        />

        {}
        {blocks.map(block => (
          <BlockNode
            key={block.id}
            block={block}
            isSelected={block.id === selectedBlockId}
            pendingPort={pendingPort}
            onSelect={onSelect}
            onDelete={onDeleteBlock}
            onPortDown={handlePortDown}
            onPortUp={handlePortUp}
            onDragEnd={onMoveBlock}
          />
        ))}
      </svg>
    </div>
  );
}
