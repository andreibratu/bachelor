import {Component, EventEmitter, Input, OnInit} from '@angular/core';
import {Movie} from '../../model/movie/movie';
import {MovieService} from '../../service/movie.service';
import {FilterStrategy} from '../../../filter/model/filter-strategy';
import {SortStrategy} from '../../../sort/model/sort-strategy';
import {FilterService} from '../../../filter/service/filter.service';
import {SortService} from '../../../sort/service/sort.service';

@Component({
  selector: 'app-movie-card-list',
  templateUrl: './movie-card-list.component.html',
  styleUrls: ['./movie-card-list.component.css']
})
export class MovieCardListComponent implements OnInit
{
  movies: Movie[];
  moviesDisplay: Movie[];
  sortStrategy: SortStrategy = null;
  deleteMovieEmitter: EventEmitter<number>;
  @Input() newMovieEmitter: EventEmitter<Movie>;
  @Input() editMovieOpenModalEmitter: EventEmitter<Movie>;
  @Input() movieFilterEmitter: EventEmitter<FilterStrategy[]>;
  @Input() movieSortEmitter: EventEmitter<SortStrategy>;

  constructor(
    private movieService: MovieService,
    private filterService: FilterService,
    private sortService: SortService
  )
  {
    this.movies = [];
    this.deleteMovieEmitter = new EventEmitter<number>();
  }

  ngOnInit(): void
  {
    this.movieService.getAllMovies().subscribe((response: object) => {
      // @ts-ignore
      const { content } = response;
      this.movies = content;
      this.moviesDisplay = this.movies.slice();
    });
    this.newMovieEmitter.subscribe(movie => {
      this.movies.push(movie);
      this.moviesDisplay = this.movies.slice();
    });
    this.deleteMovieEmitter.subscribe(id => {
      this.movieService.deleteMovie(id).subscribe(_ => {
        this.movies = this.movies.filter(movie => movie.id !== id);
        this.moviesDisplay = this.movies.slice();
      });
    });
    this.movieFilterEmitter.subscribe((strategies: FilterStrategy[]) => {
      this.moviesDisplay = this.filterService.multipleFilter(this.movies, strategies);
      // Re-apply sorting strategy on the new filtered list.
      this.moviesDisplay = this.sortService.sort(this.moviesDisplay, this.sortStrategy);
    });
    this.movieSortEmitter.subscribe((strategy) => {
      this.moviesDisplay = this.sortService.sort(this.moviesDisplay, strategy);
      // Keep the strategy throughout modifications in the filtering
      this.sortStrategy = strategy;
    });
  }
}
