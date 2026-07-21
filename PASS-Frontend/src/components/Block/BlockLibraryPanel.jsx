import { useState } from 'react';
import { BLOCK_TYPES, BLOCK_CATEGORIES } from '../../models/blockTypes';
import './BlockLibraryPanel.css';

export default function BlockLibraryPanel({ onBlockDragStart }) {
  const [search, setSearch]           = useState('');
  const [collapsed, setCollapsed]     = useState({});

  const toggleCategory = (cat) => {
    setCollapsed(prev => ({ ...prev, [cat]: !prev[cat] }));
  };

  const filtered = search.trim().toLowerCase();

  return (
    <aside className="lib-panel">
      <div className="lib-panel__header">
        <div className="lib-panel__title">Block Library</div>
        <div className="lib-panel__search">
          <span className="lib-panel__search-icon">⌕</span>
          <input
            id="lib-search"
            className="input"
            placeholder="Search blocks…"
            value={search}
            onChange={e => setSearch(e.target.value)}
          />
        </div>
      </div>

      <div className="lib-panel__body">
        {BLOCK_CATEGORIES.map(cat => {
          const items = Object.values(BLOCK_TYPES).filter(b => {
            if (b.category !== cat) return false;
            if (filtered && !b.label.toLowerCase().includes(filtered) &&
                !b.type.toLowerCase().includes(filtered)) return false;
            return true;
          });

          if (items.length === 0) return null;

          const isOpen = !collapsed[cat];

          return (
            <div key={cat} className="lib-panel__category">
              <div
                className="lib-panel__cat-header"
                onClick={() => toggleCategory(cat)}
              >
                <span>{cat}</span>
                <span className={`lib-panel__cat-arrow ${isOpen ? 'open' : ''}`}>▶</span>
              </div>

              {isOpen && items.map(blockDef => (
                <div
                  key={blockDef.type}
                  className="lib-block-item"
                  draggable
                  onDragStart={e => {
                    e.dataTransfer.setData('blockType', blockDef.type);
                    onBlockDragStart?.(blockDef.type);
                  }}
                  title={`Drag to canvas to add a ${blockDef.label}`}
                >
                  <div className={`lib-block-item__icon icon-${cat}`}>
                    {blockDef.icon}
                  </div>
                  <div className="lib-block-item__info">
                    <div className="lib-block-item__name">{blockDef.label}</div>
                    <div className="lib-block-item__ports">
                      in:{blockDef.inputs} / out:{blockDef.outputs}
                    </div>
                  </div>
                  <span className="lib-block-item__drag-hint">⣿</span>
                </div>
              ))}
            </div>
          );
        })}
      </div>

      <div className="lib-panel__footer">
        Drag blocks onto the canvas
      </div>
    </aside>
  );
}
