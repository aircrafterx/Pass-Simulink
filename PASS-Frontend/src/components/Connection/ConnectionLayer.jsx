import { BLOCK_TYPES } from '../../models/blockTypes';
import { BLOCK_W, BLOCK_H, getPortPosition } from '../Block/BlockNode';


export default function ConnectionLayer({
  blocks,
  connections,
  pendingPort,
  mousePos,
  onDeleteConnection,
}) {

  const blockMap = Object.fromEntries(blocks.map(b => [b.id, b]));

  return (
    <g className="connection-layer">
      {}
      {connections.map((conn, idx) => {
        const srcBlock = blockMap[conn.from];
        const dstBlock = blockMap[conn.to];
        if (!srcBlock || !dstBlock) return null;

        const src = getPortPosition(srcBlock, false, conn.fromPort);
        const dst = getPortPosition(dstBlock, true,  conn.toPort);


        const dx = Math.abs(dst.x - src.x) * 0.5;
        const cp1x = src.x + dx;
        const cp2x = dst.x - dx;
        const d = `M ${src.x} ${src.y} C ${cp1x} ${src.y} ${cp2x} ${dst.y} ${dst.x} ${dst.y}`;

        const midX = (src.x + dst.x) / 2;
        const midY = (src.y + dst.y) / 2;

        return (
          <g key={idx}>
            {}
            <path
              d={d}
              fill="none"
              stroke="var(--accent)"
              strokeWidth={5}
              strokeOpacity={0.12}
              strokeLinecap="round"
            />
            {}
            <path
              d={d}
              fill="none"
              stroke="var(--accent)"
              strokeWidth={1.8}
              strokeLinecap="round"
              style={{ cursor: 'pointer' }}
              onClick={() => onDeleteConnection(conn.from, conn.fromPort, conn.to, conn.toPort)}
            >
              <title>Click to delete this connection</title>
            </path>

            {}
            <circle
              cx={dst.x} cy={dst.y} r={3}
              fill="var(--accent)"
              style={{ pointerEvents: 'none' }}
            />

            {}
            <circle
              cx={midX} cy={midY}
              r={7}
              fill="var(--bg-panel-3)"
              stroke="var(--border)"
              strokeWidth={1}
              style={{ cursor: 'pointer', opacity: 0 }}
              className="conn-delete-btn"
              onClick={() => onDeleteConnection(conn.from, conn.fromPort, conn.to, conn.toPort)}
            />
          </g>
        );
      })}

      {}
      {pendingPort && mousePos && (() => {
        const srcBlock = blockMap[pendingPort.blockId];
        if (!srcBlock) return null;

        const src = pendingPort.isInput
          ? getPortPosition(srcBlock, true,  pendingPort.portIndex)
          : getPortPosition(srcBlock, false, pendingPort.portIndex);
        const dst = mousePos;

        const dx  = Math.abs(dst.x - src.x) * 0.5;
        const cp1x = pendingPort.isInput ? src.x - dx : src.x + dx;
        const cp2x = pendingPort.isInput ? dst.x + dx : dst.x - dx;
        const d = `M ${src.x} ${src.y} C ${cp1x} ${src.y} ${cp2x} ${dst.y} ${dst.x} ${dst.y}`;

        return (
          <path
            d={d}
            fill="none"
            stroke="var(--accent)"
            strokeWidth={1.5}
            strokeDasharray="6 4"
            strokeOpacity={0.7}
            strokeLinecap="round"
            style={{ pointerEvents: 'none' }}
          />
        );
      })()}
    </g>
  );
}
