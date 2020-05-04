import {Component, EventEmitter, Input, OnInit} from '@angular/core';
import {Movie} from '../../model/movie/movie';

@Component({
  selector: 'app-movie-card',
  templateUrl: './movie-card.component.html',
  styleUrls: ['./movie-card.component.css']
})
export class MovieCardComponent implements OnInit
{
  @Input() movie: Movie;
  @Input() deleteMovieHandler: EventEmitter<number>;
  @Input() editMovieOpenModalHandler: EventEmitter<Movie>;

  constructor() { }

  ngOnInit(): void {}

  onDelete()
  {
    this.deleteMovieHandler.emit(this.movie.id);
  }

  onEdit()
  {
    this.editMovieOpenModalHandler.emit(this.movie);
  }
}
