import { useState } from 'react';
import './ScopePanel.css';


export default function ScopePanel({ scopeData, simStatus, settings }) {
  const scopeIds = Object.keys(scopeData);
  const [activeScope, setActiveScope] = useState(null);

  const currentId = activeScope && scopeIds.includes(activeScope)
    ? activeScope
    : scopeIds[0] ?? null;

  const values = currentId ? (scopeData[currentId] ?? []) : [];

  const expectedSteps = settings
    ? Math.round((settings.endTime - settings.startTime) / settings.stepSize) + 1
    : null;

  return (
    <div className="scope-panel">
      <div className="scope-panel__header">
        <span className="scope-panel__title">Scope</span>
        {currentId && (
          <>
            <span className="scope-panel__scope-name">{currentId}</span>
            <span className="scope-panel__count">
              {values.length} sample{values.length !== 1 ? 's' : ''}
            </span>
          </>
        )}

        {}
        {scopeIds.length > 1 && (
          <div className="scope-panel__tabs" style={{ marginLeft: 'auto' }}>
            {scopeIds.map(sid => (
              <button
                key={sid}
                className={`scope-panel__tab ${sid === currentId ? 'active' : ''}`}
                onClick={() => setActiveScope(sid)}
              >
                {sid}
              </button>
            ))}
          </div>
        )}
      </div>

      <div className="scope-panel__body">
        {values.length === 0 ? (
          <div className="scope-panel__empty">
            {simStatus === 'running'
              ? '⏳ Simulation running…'
              : scopeIds.length === 0
                ? '📊 Add a Scope block and run simulation to see output'
                : '📊 Run the simulation to see scope data'}
          </div>
        ) : (
          <ScopeChart values={values} scopeId={currentId} expectedSteps={expectedSteps} />
        )}
      </div>
    </div>
  );
}


function ScopeChart({ values, scopeId, expectedSteps }) {
  const W = 3000;
  const H = 160;
  const PX = 40;
  const PY = 16;

  const n    = expectedSteps && expectedSteps > values.length ? expectedSteps : values.length;
  const minV = Math.min(...values);
  const maxV = Math.max(...values);
  const rng  = maxV - minV || 1;

  const toX = (i) => PX + (i / (n - 1 || 1)) * (W - PX - 8);
  const toY = (v) => PY + (1 - (v - minV) / rng) * (H - 2 * PY);


  const points = values.map((v, i) => `${toX(i)},${toY(v)}`).join(' ');


  const yTicks = 5;
  const yLabels = Array.from({ length: yTicks }, (_, i) => {
    const ratio = i / (yTicks - 1);
    const val   = minV + ratio * rng;
    const y     = H - PY - ratio * (H - 2 * PY);
    return { val, y };
  });

  return (
    <svg
      viewBox={`0 0 ${W} ${H}`}
      preserveAspectRatio="none"
      style={{ width: '100%', height: '100%', display: 'block' }}
    >
      <defs>
        <linearGradient id="scopeGrad" x1="0" y1="0" x2="0" y2="1">
          <stop offset="0%"   stopColor="var(--accent)" stopOpacity={0.3} />
          <stop offset="100%" stopColor="var(--accent)" stopOpacity={0}   />
        </linearGradient>
      </defs>

      {}
      {yLabels.map(({ val, y }, i) => (
        <g key={i}>
          <line
            x1={PX} y1={y} x2={W - 8} y2={y}
            stroke="rgba(255,255,255,0.04)"
            strokeWidth={1}
          />
          <text
            x={PX - 4} y={y}
            textAnchor="end"
            dominantBaseline="middle"
            fontSize={14}
            fill="rgba(138,150,176,0.7)"
          >
            {val.toFixed(2)}
          </text>
        </g>
      ))}

      {}
      {values.length > 0 && (
        <polygon
          points={`${toX(0)},${H - PY} ${points} ${toX(values.length - 1)},${H - PY}`}
          fill="url(#scopeGrad)"
        />
      )}

      {}
      <polyline
        points={points}
        fill="none"
        stroke="var(--accent)"
        strokeWidth={3}
        strokeLinecap="round"
        strokeLinejoin="round"
        style={{ filter: 'drop-shadow(0 0 4px var(--accent))' }}
      />

      {}
      {values.length <= 50 && values.map((v, i) => (
        <circle
          key={i}
          cx={toX(i)} cy={toY(v)} r={4}
          fill="var(--accent)"
          stroke="var(--bg-panel)"
          strokeWidth={2}
        />
      ))}

      {}
      {minV < 0 && maxV > 0 && (
        <line
          x1={PX} y1={toY(0)} x2={W - 8} y2={toY(0)}
          stroke="rgba(255,255,255,0.15)"
          strokeWidth={1}
          strokeDasharray="6 4"
        />
      )}
    </svg>
  );
}
