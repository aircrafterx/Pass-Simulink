import './SimulationControls.css';

export default function SimulationControls({
  settings,
  onSettingsChange,
  onRun,
  simStatus,
  simError,
}) {
  const isRunning = simStatus === 'running';

  return (
    <div className="sim-controls">
      <span className="sim-controls__label">Simulation</span>

      <div className="sim-controls__sep" />

      {}
      <div className="sim-controls__field">
        <label htmlFor="sim-start">Start</label>
        <input
          id="sim-start"
          className="input"
          type="number"
          step={0.1}
          value={settings.startTime}
          onChange={e => onSettingsChange({ startTime: parseFloat(e.target.value) })}
          disabled={isRunning}
        />
      </div>

      {}
      <div className="sim-controls__field">
        <label htmlFor="sim-end">End</label>
        <input
          id="sim-end"
          className="input"
          type="number"
          step={0.1}
          min={0.01}
          value={settings.endTime}
          onChange={e => onSettingsChange({ endTime: parseFloat(e.target.value) })}
          disabled={isRunning}
        />
      </div>

      {}
      <div className="sim-controls__field">
        <label htmlFor="sim-step">Step</label>
        <input
          id="sim-step"
          className="input"
          type="number"
          step={0.01}
          min={0.001}
          value={settings.stepSize}
          onChange={e => onSettingsChange({ stepSize: parseFloat(e.target.value) })}
          disabled={isRunning}
        />
      </div>

      <div className="sim-controls__sep" />

      {simError && (
        <span className="sim-controls__error" title={simError}>
          ⚠ {simError}
        </span>
      )}

      <div className="sim-controls__spacer" />

      <button
        id="sim-run-btn"
        className={`btn ${isRunning ? '' : 'btn-success'}`}
        onClick={onRun}
        disabled={isRunning}
      >
        {isRunning ? '⏳ Running…' : '▶ Run Simulation'}
      </button>
    </div>
  );
}
