import {Component, ElementRef, EventEmitter, Input, OnInit, ViewChild} from '@angular/core';
import {MovieService} from '../../service/movie.service';
import {NgbModal} from '@ng-bootstrap/ng-bootstrap';
import {Movie} from '../../model/movie/movie';

@Component({
  selector: 'app-movie-edit-modal',
  templateUrl: './movie-edit-modal.component.html',
  styleUrls: ['./movie-edit-modal.component.css']
})
export class MovieEditModalComponent implements OnInit
{
  @Input() editMovieOpenModalEmitter: EventEmitter<Movie>;
  @ViewChild('content') modal: ElementRef;
  @ViewChild('movieEditForm') form: ElementRef;
  model: Movie;

  constructor(private movieService: MovieService, private modalService: NgbModal) {}

  ngOnInit(): void
  {
    this.editMovieOpenModalEmitter.subscribe(movie => {
      this.model = movie;
      this.modalService.open(this.model).result.then(
        (_) => this.movieService.putMovie(this.model).subscribe(() => {}),
        () => {}
      );
    });
  }

  onSubmit(form)
  {
    form.reset();
  }
}
