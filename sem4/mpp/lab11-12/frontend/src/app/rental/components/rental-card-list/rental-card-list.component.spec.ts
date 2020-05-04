import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { RentalCardListComponent } from './rental-card-list.component';

describe('RentalCardListComponent', () => {
  let component: RentalCardListComponent;
  let fixture: ComponentFixture<RentalCardListComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ RentalCardListComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(RentalCardListComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
