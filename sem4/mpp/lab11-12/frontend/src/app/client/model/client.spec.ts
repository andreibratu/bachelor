import { Client } from './client';

describe('Client', () => {
  it('should create an instance', () => {
    expect(new Client(5, 'Andrei', 'Gheorghe 6')).toBeTruthy();
  });
});
