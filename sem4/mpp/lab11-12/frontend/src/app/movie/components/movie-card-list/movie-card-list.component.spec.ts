import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { MovieCardListComponent } from './movie-card-list.component';

describe('MovieCardListComponent', () => {
  let component: MovieCardListComponent;
  let fixture: ComponentFixture<MovieCardListComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ MovieCardListComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(MovieCardListComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
