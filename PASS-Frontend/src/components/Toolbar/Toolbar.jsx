import './Toolbar.css';

export default function Toolbar({
  simStatus,
  onRun,
  onSave,
  onLoad,
  onClear,
}) {
  const statusLabel = {
    idle:    'Ready',
    running: 'Running…',
    done:    'Simulation Done',
    error:   'Error',
  }[simStatus] ?? 'Ready';

  return (
    <header className="toolbar">
      {}
      <div className="toolbar__logo">
        <div className="toolbar__logo-mark">⚡</div>
        <div>
          <div className="toolbar__logo-text">PASS</div>
          <div className="toolbar__logo-sub">Simulink</div>
        </div>
      </div>

      <div className="toolbar__sep" />

      {}
      <div className="toolbar__group">
        <button
          id="toolbar-new"
          className="btn"
          onClick={onClear}
          title="New project"
        >
          ✦ New
        </button>
        <button
          id="toolbar-save"
          className="btn"
          onClick={onSave}
          title="Save project to backend disk"
        >
          💾 Save
        </button>
        <button
          id="toolbar-load"
          className="btn"
          onClick={onLoad}
          title="Load project from backend disk"
        >
          📂 Load
        </button>
      </div>

      <div className="toolbar__sep" />

      <div className="toolbar__spacer" />

      {}
      <div className={`toolbar__status ${simStatus}`}>
        <span className={`status-dot ${simStatus}`} />
        {statusLabel}
      </div>

      {}
      <button
        id="toolbar-run"
        className="btn btn-success"
        onClick={onRun}
        disabled={simStatus === 'running'}
        title="Run simulation"
      >
        ▶ Run
      </button>
    </header>
  );
}
