import {Component, EventEmitter, Input, OnInit} from '@angular/core';
import {Movie} from '../../model/movie/movie';
import {Genre} from '../../model/genre/genre.enum';
import {MovieService} from '../../service/movie.service';

@Component({
  selector: 'app-movie-form',
  templateUrl: './movie-form.component.html',
  styleUrls: ['./movie-form.component.css']
})
export class MovieFormComponent implements OnInit
{
  @Input() newMovieEmitter: EventEmitter<Movie>;
  model: Movie = this.emptyMovie();
  genres: Genre[] = [
    Genre.ACTION,
    Genre.COMEDY,
    Genre.DOCUMENTARY,
    Genre.HORROR,
    Genre.ROMANTIC,
    Genre.THRILLER];

  constructor(private movieService: MovieService) {}

  ngOnInit(): void {}

  emptyMovie()
  {
    return new Movie(null, null, null, null);
  }

  onSubmit(form)
  {
    this.movieService.createMovie(this.model).subscribe((movie: Movie) => {
      this.newMovieEmitter.emit(movie);
    });
    this.model = this.emptyMovie();
    form.reset();
  }
}
