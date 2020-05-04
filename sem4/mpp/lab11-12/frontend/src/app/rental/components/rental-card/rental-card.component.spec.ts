import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { RentalCardComponent } from './rental-card.component';

describe('RentalCardComponent', () => {
  let component: RentalCardComponent;
  let fixture: ComponentFixture<RentalCardComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ RentalCardComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(RentalCardComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
