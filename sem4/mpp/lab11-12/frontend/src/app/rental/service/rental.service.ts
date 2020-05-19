// @ts-nocheck

import { Injectable } from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {forkJoin, Observable} from 'rxjs';
import {map} from 'rxjs/operators';
import {Rental} from '../model/rental';

@Injectable({
  providedIn: 'root'
})
export class RentalService
{

  ROOT_URL = 'http://localhost:8080';
  CLIENTS_URL = this.ROOT_URL + '/clients';
  MOVIES_URL = this.ROOT_URL + '/movies';
  RENTALS_URL = this.ROOT_URL + '/rentals';

  constructor(
    private http: HttpClient,
  ) { }

  getAllRentals(): Observable<object>
  {
    return forkJoin([
      this.http.get(this.RENTALS_URL),
      this.http.get(this.CLIENTS_URL),
      this.http.get(this.MOVIES_URL)]
    ).pipe(map((response: object[]) => {
      let [rentals, clients, movies] = response;
      rentals = rentals.content;
      clients = clients.content;
      movies = movies.content;
      console.log(rentals, clients, movies);
      const wow = rentals.map(received => ({
            id: received.id,
            movie: movies.find(movie => movie.id === received.movieID),
            client: clients.find(client => client.id === received.clientID),
            startDate: received.startDate,
            endDate: received.endDate != null ? received.endDate : null
        }));
      console.log(wow);
      return wow;
      }));
  }

  createRental(rental: {clientID: number, movieID: number}): Observable<object>
  {
    console.log(rental);
    const payload = {
      clientID: rental.clientID,
      movieID: rental.movieID,
      startDate: (new Date()).toISOString(),
      endDate: null
    };
    return this.http.post(this.RENTALS_URL, payload);
  }

  checkInRental(rental: Rental)
  {
    const payload = {
      id: rental.id,
      clientID: rental.client.id,
      movieID: rental.movie.id,
      startDate: rental.startDate,
      endDate: (new Date()).toISOString()
    };
    this.http.put(this.RENTALS_URL + `/${rental.id}`, payload).subscribe((_) => {});
  }
}
