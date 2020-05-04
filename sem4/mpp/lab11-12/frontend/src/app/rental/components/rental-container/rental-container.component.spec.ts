import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { RentalContainerComponent } from './rental-container.component';

describe('RentalContainerComponent', () => {
  let component: RentalContainerComponent;
  let fixture: ComponentFixture<RentalContainerComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ RentalContainerComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(RentalContainerComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
