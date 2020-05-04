import { Injectable } from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {Observable} from 'rxjs';
import {Movie} from '../model/movie/movie';

@Injectable({
  providedIn: 'root'
})
export class MovieService
{
  SERVER_URL = 'http://localhost:8080/movies';

  constructor(private http: HttpClient) { }

  getAllMovies(): Observable<object>
  {
    return this.http.get<Movie[]>(this.SERVER_URL);
  }

  createMovie(movie: Movie): Observable<object>
  {
    const payload = {title: movie.title, genre: (movie.genre), year: movie.year};
    console.log(payload);
    return this.http.post(this.SERVER_URL, payload);
  }

  deleteMovie(id: number): Observable<object>
  {
    return this.http.delete(this.SERVER_URL + `/${id}`);
  }

  putMovie(movie: Movie): Observable<object>
  {
    return this.http.put(this.SERVER_URL + `/${movie.id}`, movie);
  }
}
