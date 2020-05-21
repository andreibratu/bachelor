import {Component, EventEmitter, Input} from '@angular/core';
import {RentalService} from '../../service/rental.service';
import {ClientService} from '../../../client/service/client.service';
import {MovieService} from '../../../movie/service/movie.service';
import {Movie} from '../../../movie/model/movie/movie';
import {Client} from '../../../client/model/client';

@Component({
  selector: 'app-rental-form',
  templateUrl: './rental-form.component.html',
  styleUrls: ['./rental-form.component.css']
})
export class RentalFormComponent
{
  @Input() fetchRentalsEmitter: EventEmitter<boolean>;
  clients: {id: number, name: string}[];
  movies: {id: number, title: string}[];
  model: {clientID: number, movieID: number};

  constructor(
    private rentalService: RentalService,
    private clientService: ClientService,
    private movieService: MovieService
  ) {
    this.model = this.emptyModel();
    this.movieService.getAllMovies().subscribe((response: Movie[]) => {
      this.movies = response.map(movie => ({id: movie.id, title: movie.title}));
    });
    this.clientService.getAllClients().subscribe((response: Client[]) => {
      this.clients = response.map(client => ({id: client.id, name: client.name}));
    });
  }

  emptyModel()
  {
    return {clientID: null, movieID: null};
  }

  onSubmit(form)
  {
    this.rentalService.createRental(this.model).subscribe(
      (_) => this.fetchRentalsEmitter.emit(true)
    );
    form.reset();
    this.model = this.emptyModel();
  }
}
