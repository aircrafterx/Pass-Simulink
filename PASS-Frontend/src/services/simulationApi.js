

const BASE_URL = 'http://127.0.0.1:8085';

async function apiFetch(path, options = {}) {
  const res = await fetch(`${BASE_URL}${path}`, {
    headers: { 'Content-Type': 'application/json', ...options.headers },
    ...options,
  });
  const data = await res.json();
  if (!res.ok) {
    throw new Error(data.error ?? `HTTP ${res.status}`);
  }
  return data;
}


export async function getBlockCatalog() {
  return apiFetch('/api/blocks/catalog');
}


export async function runSimulation(project) {
  return apiFetch('/api/simulate', {
    method: 'POST',
    body: JSON.stringify(project),
  });
}


export async function saveProject(project) {
  return apiFetch('/api/save', {
    method: 'POST',
    body: JSON.stringify(project),
  });
}


export async function loadProject() {
  return apiFetch('/api/load');
}
