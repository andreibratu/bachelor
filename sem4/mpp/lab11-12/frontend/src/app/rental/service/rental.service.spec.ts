import { TestBed } from '@angular/core/testing';

import { RentalService } from './rental.service';

describe('RentalServiceService', () => {
  let service: RentalService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(RentalService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
