import { useRef, useState } from 'react';
import { BLOCK_TYPES } from '../../models/blockTypes';
import './BlockNode.css';


export const BLOCK_W = 130;
export const BLOCK_H = 56;


export function getPortPosition(block, isInput, portIndex) {
  const x = isInput
    ? block.x
    : block.x + BLOCK_W;
  const bh = BLOCK_H;
  const def = BLOCK_TYPES[block.type];
  const count = isInput ? (def?.inputs ?? 0) : (def?.outputs ?? 0);
  const spacing = bh / (count + 1);
  const y = block.y + spacing * (portIndex + 1);
  return { x, y };
}

export default function BlockNode({
  block,
  isSelected,
  pendingPort,
  onSelect,
  onDelete,
  onPortDown,
  onPortUp,
  onDragEnd,
}) {
  const def = BLOCK_TYPES[block.type];
  if (!def) return null;

  const dragOffset = useRef({ dx: 0, dy: 0 });
  const dragging   = useRef(false);


  const onMouseDown = (e) => {

    if (e.target.classList.contains('block-node__port')) return;
    if (e.target.classList.contains('block-node__delete')) return;

    e.stopPropagation();
    onSelect(block.id);
    dragging.current   = true;
    dragOffset.current = {
      dx: e.clientX - block.x,
      dy: e.clientY - block.y,
    };

    const onMove = (me) => {
      if (!dragging.current) return;
      const nx = me.clientX - dragOffset.current.dx;
      const ny = me.clientY - dragOffset.current.dy;
      onDragEnd(block.id, Math.max(0, nx), Math.max(0, ny));
    };
    const onUp = () => {
      dragging.current = false;
      window.removeEventListener('mousemove', onMove);
      window.removeEventListener('mouseup',  onUp);
    };
    window.addEventListener('mousemove', onMove);
    window.addEventListener('mouseup',   onUp);
  };


  const handlePortDown = (e, isInput, portIndex) => {
    e.stopPropagation();
    onPortDown(block.id, isInput, portIndex);
  };

  const handlePortUp = (e, isInput, portIndex) => {
    e.stopPropagation();
    onPortUp(block.id, isInput, portIndex);
  };

  const isActivePending = pendingPort?.blockId === block.id;

  return (
    <g
      className={`block-node ${isSelected ? 'block-node--selected' : ''} block-node--${def.category}`}
      transform={`translate(${block.x}, ${block.y})`}
      onMouseDown={onMouseDown}
      onClick={e => { e.stopPropagation(); onSelect(block.id); }}
    >
      {}
      <rect
        className="block-node__body"
        x={0}
        y={0}
        width={BLOCK_W}
        height={BLOCK_H}
        rx={10}
        ry={10}
        style={{
          fill:   'var(--bg-panel-2)',
          stroke: isSelected ? 'var(--accent)' : 'var(--border)',
          strokeWidth: isSelected ? 1.5 : 1,
          filter: isSelected ? 'drop-shadow(0 0 6px var(--accent-glow))' : 'none',
        }}
      />

      {}
      <rect
        x={0} y={0}
        width={4} height={BLOCK_H}
        rx={3}
        ry={3}
        style={{
          fill: def.category === 'Sources'
            ? 'var(--block-source)'
            : def.category === 'Math'
              ? 'var(--block-math)'
              : 'var(--block-sink)',
        }}
      />

      {}
      <text
        x={16} y={21}
        fontSize={14}
        textAnchor="middle"
        dominantBaseline="middle"
        style={{ userSelect: 'none' }}
      >
        {def.icon}
      </text>

      {}
      <text
        x={30} y={20}
        fontSize={11}
        fontWeight={600}
        fill="var(--text-primary)"
        dominantBaseline="middle"
        style={{ userSelect: 'none', fontFamily: 'Inter, sans-serif' }}
      >
        {def.label}
      </text>

      {}
      <text
        x={10} y={40}
        fontSize={9}
        fill="var(--text-muted)"
        fontFamily="'JetBrains Mono', monospace"
        style={{ userSelect: 'none' }}
      >
        {block.id.length > 16 ? block.id.slice(0, 14) + '…' : block.id}
      </text>

      {}
      {isSelected && (
        <g
          onClick={e => { e.stopPropagation(); onDelete(block.id); }}
          style={{ cursor: 'pointer' }}
        >
          <rect
            x={BLOCK_W - 18} y={4}
            width={14} height={14}
            rx={3} ry={3}
            fill="var(--danger-dim)"
            stroke="var(--danger)"
            strokeWidth={0.8}
          />
          <text
            x={BLOCK_W - 11} y={12}
            fontSize={9}
            textAnchor="middle"
            dominantBaseline="middle"
            fill="var(--danger)"
            style={{ userSelect: 'none' }}
          >
            ✕
          </text>
        </g>
      )}

      {}
      {Array.from({ length: def.inputs }).map((_, i) => {
        const spacing = BLOCK_H / (def.inputs + 1);
        const py = spacing * (i + 1);
        const isPending = isActivePending && pendingPort.isInput && pendingPort.portIndex === i;
        return (
          <circle
            key={`in-${i}`}
            cx={0} cy={py}
            r={6}
            className={`block-node__port ${isPending ? 'block-node__port--active' : ''}`}
            style={{
              fill:   isPending ? 'var(--accent)' : 'var(--bg-panel-3)',
              stroke: isPending ? 'var(--accent)' : 'var(--border-bright)',
              strokeWidth: 2,
              cursor: 'crosshair',
            }}
            onMouseDown={e => handlePortDown(e, true, i)}
            onMouseUp={e => handlePortUp(e, true, i)}
          />
        );
      })}

      {}
      {Array.from({ length: def.outputs }).map((_, i) => {
        const spacing = BLOCK_H / (def.outputs + 1);
        const py = spacing * (i + 1);
        const isPending = isActivePending && !pendingPort.isInput && pendingPort.portIndex === i;
        return (
          <circle
            key={`out-${i}`}
            cx={BLOCK_W} cy={py}
            r={6}
            className={`block-node__port ${isPending ? 'block-node__port--active' : ''}`}
            style={{
              fill:   isPending ? 'var(--accent)' : 'var(--bg-panel-3)',
              stroke: isPending ? 'var(--accent)' : 'var(--border-bright)',
              strokeWidth: 2,
              cursor: 'crosshair',
            }}
            onMouseDown={e => handlePortDown(e, false, i)}
            onMouseUp={e => handlePortUp(e, false, i)}
          />
        );
      })}
    </g>
  );
}
