import {Component, EventEmitter, Input, OnInit} from '@angular/core';
import {Movie} from '../../model/movie/movie';
import {FilterStrategy} from '../../../filter/model/filter-strategy';
import {SortStrategy} from '../../../sort/model/sort-strategy';

@Component({
  selector: 'app-movie-container',
  templateUrl: './movie-container.component.html',
  styleUrls: ['./movie-container.component.css']
})
export class MovieContainerComponent implements OnInit
{
  newMovieEmitter: EventEmitter<Movie>;
  editMovieOpenModalEmitter: EventEmitter<Movie>;
  movieFilterEmitter: EventEmitter<FilterStrategy>;
  movieSortEmitter: EventEmitter<SortStrategy>;

  constructor()
  {
    this.newMovieEmitter = new EventEmitter<Movie>();
    this.editMovieOpenModalEmitter = new EventEmitter<Movie>();
    this.movieFilterEmitter = new EventEmitter<FilterStrategy>();
    this.movieSortEmitter = new EventEmitter<SortStrategy>();
  }

  ngOnInit(): void {}
}
