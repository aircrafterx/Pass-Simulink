

export const BLOCK_CATEGORIES = ['Sources', 'Math', 'Sinks'];

export const BLOCK_TYPES = {

  Clock: {
    type:     'Clock',
    category: 'Sources',
    label:    'Clock',
    icon:     '⏱',
    inputs:   0,
    outputs:  1,
    defaultParams: { stepSize: 1.0 },
    paramDefs: [
      { key: 'stepSize', label: 'Step Size', min: 0.001, step: 0.01 },
    ],
  },
  Sine: {
    type:     'Sine',
    category: 'Sources',
    label:    'Sine Wave',
    icon:     '〜',
    inputs:   1,
    outputs:  1,
    defaultParams: { amplitude: 1.0, frequency: 1.0, phaseOffset: 0.0 },
    paramDefs: [
      { key: 'amplitude',   label: 'Amplitude',    min: -1e9, step: 0.1 },
      { key: 'frequency',   label: 'Frequency',    min: 0,    step: 0.1 },
      { key: 'phaseOffset', label: 'Phase Offset', min: -1e9, step: 0.1 },
    ],
  },
  Cosine: {
    type:     'Cosine',
    category: 'Sources',
    label:    'Cosine Wave',
    icon:     '∿',
    inputs:   1,
    outputs:  1,
    defaultParams: { amplitude: 1.0, frequency: 1.0, phaseOffset: 0.0 },
    paramDefs: [
      { key: 'amplitude',   label: 'Amplitude',    min: -1e9, step: 0.1 },
      { key: 'frequency',   label: 'Frequency',    min: 0,    step: 0.1 },
      { key: 'phaseOffset', label: 'Phase Offset', min: -1e9, step: 0.1 },
    ],
  },


  Gain: {
    type:     'Gain',
    category: 'Math',
    label:    'Gain',
    icon:     '×',
    inputs:   1,
    outputs:  1,
    defaultParams: { gain: 1.0 },
    paramDefs: [
      { key: 'gain', label: 'Gain Factor', min: -1e9, step: 0.1 },
    ],
  },
  Add: {
    type:     'Add',
    category: 'Math',
    label:    'Add',
    icon:     '+',
    inputs:   2,
    outputs:  1,
    defaultParams: {},
    paramDefs: [],
  },
  Subtract: {
    type:     'Subtract',
    category: 'Math',
    label:    'Subtract',
    icon:     '−',
    inputs:   2,
    outputs:  1,
    defaultParams: {},
    paramDefs: [],
  },
  Multiply: {
    type:     'Multiply',
    category: 'Math',
    label:    'Multiply',
    icon:     '×',
    inputs:   2,
    outputs:  1,
    defaultParams: {},
    paramDefs: [],
  },
  Average: {
    type:     'Average',
    category: 'Math',
    label:    'Average',
    icon:     'μ',
    inputs:   2,
    outputs:  1,
    defaultParams: {},
    paramDefs: [],
  },
  Min: {
    type:     'Min',
    category: 'Math',
    label:    'Min',
    icon:     '↓',
    inputs:   2,
    outputs:  1,
    defaultParams: {},
    paramDefs: [],
  },
  Max: {
    type:     'Max',
    category: 'Math',
    label:    'Max',
    icon:     '↑',
    inputs:   2,
    outputs:  1,
    defaultParams: {},
    paramDefs: [],
  },


  Scope: {
    type:     'Scope',
    category: 'Sinks',
    label:    'Scope',
    icon:     '📈',
    inputs:   1,
    outputs:  0,
    defaultParams: {},
    paramDefs: [],
  },
};

export const getCategoryColor = (category) => {
  switch (category) {
    case 'Sources': return 'var(--block-source)';
    case 'Math':    return 'var(--block-math)';
    case 'Sinks':   return 'var(--block-sink)';
    default:        return 'var(--text-secondary)';
  }
};

export const getCategoryClass = (category) => {
  switch (category) {
    case 'Sources': return 'badge-source';
    case 'Math':    return 'badge-math';
    case 'Sinks':   return 'badge-sink';
    default:        return '';
  }
};
