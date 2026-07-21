import { useState } from 'react';
import { BLOCK_TYPES, getCategoryClass } from '../../models/blockTypes';
import './PropertiesPanel.css';

export default function PropertiesPanel({
  block,
  onParamChange,
  onIdChange,
  onDelete,
}) {
  const [editingId, setEditingId] = useState(false);
  const [idDraft,   setIdDraft]   = useState('');

  if (!block) {
    return (
      <aside className="props-panel">
        <div className="props-panel__header">
          <div className="props-panel__title">Properties</div>
        </div>
        <div className="props-panel__empty">
          <div className="props-panel__empty-icon">⬡</div>
          <div className="props-panel__empty-text">
            Click a block on the canvas to view and edit its properties
          </div>
        </div>
      </aside>
    );
  }

  const def = BLOCK_TYPES[block.type];

  const startEditId = () => {
    setIdDraft(block.id);
    setEditingId(true);
  };

  const commitId = () => {
    const trimmed = idDraft.trim();
    if (trimmed && trimmed !== block.id) {
      onIdChange(block.id, trimmed);
    }
    setEditingId(false);
  };

  const catClass = getCategoryClass(def?.category ?? '');

  return (
    <aside className="props-panel">
      <div className="props-panel__header">
        <div className="props-panel__title">Properties</div>
        <div className="props-panel__block-type">
          <span className={`badge ${catClass}`}>{def?.category ?? block.type}</span>
          <span style={{ fontSize: 13 }}>{def?.icon}</span>
          <span style={{ fontSize: 12, fontWeight: 600, color: 'var(--text-primary)' }}>
            {def?.label ?? block.type}
          </span>
        </div>
      </div>

      <div className="props-panel__body">
        {}
        <div className="props-panel__port-info" style={{ marginBottom: 14 }}>
          <div className="props-panel__port-item">
            <span className="props-panel__port-count">{def?.inputs ?? 0}</span>
            <span className="props-panel__port-label">Inputs</span>
          </div>
          <div className="props-panel__port-sep" />
          <div className="props-panel__port-item">
            <span className="props-panel__port-count">{def?.outputs ?? 0}</span>
            <span className="props-panel__port-label">Outputs</span>
          </div>
        </div>

        {}
        <div className="props-field">
          <label className="props-field__label">Block ID</label>
          {editingId ? (
            <div className="props-field__row">
              <input
                id="prop-block-id"
                className="input"
                value={idDraft}
                autoFocus
                onChange={e => setIdDraft(e.target.value)}
                onBlur={commitId}
                onKeyDown={e => {
                  if (e.key === 'Enter') commitId();
                  if (e.key === 'Escape') setEditingId(false);
                }}
              />
            </div>
          ) : (
            <div className="props-field__row">
              <input
                className="input"
                value={block.id}
                readOnly
                style={{ fontFamily: 'JetBrains Mono, monospace', fontSize: 11 }}
              />
              <button
                id="prop-edit-id"
                className="btn props-field__id-btn"
                onClick={startEditId}
                title="Edit block ID"
              >✎</button>
            </div>
          )}
          <div className="props-panel__hint">Must be unique across all blocks</div>
        </div>

        {}
        <div className="props-panel__section-title">Parameters</div>
        {(def?.paramDefs?.length ?? 0) === 0 ? (
          <div className="props-panel__no-params">No configurable parameters</div>
        ) : (
          def.paramDefs.map(pd => (
            <div key={pd.key} className="props-field">
              <label htmlFor={`prop-${pd.key}`} className="props-field__label">
                {pd.label}
              </label>
              <input
                id={`prop-${pd.key}`}
                className="input"
                type="number"
                step={pd.step ?? 0.1}
                min={pd.min}
                max={pd.max}
                value={block.params[pd.key] ?? def.defaultParams[pd.key] ?? 0}
                onChange={e => onParamChange(block.id, { [pd.key]: parseFloat(e.target.value) })}
              />
            </div>
          ))
        )}
      </div>

      {}
      <div className="props-panel__delete">
        <button
          id="prop-delete-block"
          className="btn btn-danger"
          style={{ width: '100%', justifyContent: 'center' }}
          onClick={() => onDelete(block.id)}
        >
          🗑 Delete Block
        </button>
      </div>
    </aside>
  );
}
