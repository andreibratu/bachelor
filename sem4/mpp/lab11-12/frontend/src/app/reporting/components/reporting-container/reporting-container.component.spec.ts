import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { ReportingContainerComponent } from './reporting-container.component';

describe('ReportingContainerComponent', () => {
  let component: ReportingContainerComponent;
  let fixture: ComponentFixture<ReportingContainerComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ ReportingContainerComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(ReportingContainerComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
