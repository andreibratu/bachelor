import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { MovieEditModalComponent } from './movie-edit-modal.component';

describe('EditMovieModalComponent', () => {
  let component: MovieEditModalComponent;
  let fixture: ComponentFixture<MovieEditModalComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ MovieEditModalComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(MovieEditModalComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
