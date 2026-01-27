const BACKEND_URL = process.env.REACT_APP_BACKEND_URL || 'http://localhost:3030';

interface RequestOptions {
  method: 'GET' | 'POST' | 'PUT' | 'DELETE';
  body?: any;
}

class BackendService {
  private async request<T>(endpoint: string, options: RequestOptions): Promise<T> {
    const url = `${BACKEND_URL}${endpoint}`;
    
    const fetchOptions: RequestInit = {
      method: options.method,
      headers: {
        'Content-Type': 'application/json',
      },
    };

    if (options.body) {
      fetchOptions.body = JSON.stringify(options.body);
    }

    try {
      const response = await fetch(url, fetchOptions);
      
      if (!response.ok) {
        throw new Error(`API Error: ${response.status} ${response.statusText}`);
      }

      return await response.json();
    } catch (error) {
      console.error(`Request to ${url} failed:`, error);
      throw error;
    }
  }

  async get<T>(endpoint: string): Promise<T> {
    return this.request<T>(endpoint, { method: 'GET' });
  }

  async post<T>(endpoint: string, body: any): Promise<T> {
    return this.request<T>(endpoint, { method: 'POST', body });
  }

  async put<T>(endpoint: string, body: any): Promise<T> {
    return this.request<T>(endpoint, { method: 'PUT', body });
  }

  async delete<T>(endpoint: string): Promise<T> {
    return this.request<T>(endpoint, { method: 'DELETE' });
  }
}

export const backendService = new BackendService();
