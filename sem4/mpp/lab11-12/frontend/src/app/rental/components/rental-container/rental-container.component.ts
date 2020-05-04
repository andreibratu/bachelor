import {Component, EventEmitter} from '@angular/core';

@Component({
  selector: 'app-rental-container',
  templateUrl: './rental-container.component.html',
  styleUrls: ['./rental-container.component.css']
})
export class RentalContainerComponent
{
  fetchRentalsEmitter: EventEmitter<boolean>;

  constructor()
  {
    this.fetchRentalsEmitter = new EventEmitter<boolean>();
  }
}
