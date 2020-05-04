import {Component, EventEmitter, Input, OnInit} from '@angular/core';
import {Rental} from '../../model/rental';
import {RentalService} from '../../service/rental.service';

@Component({
  selector: 'app-rental-card',
  templateUrl: './rental-card.component.html',
  styleUrls: ['./rental-card.component.css']
})
export class RentalCardComponent implements OnInit
{
  @Input() fetchRentalsEmitter: EventEmitter<boolean>;
  @Input() rental: Rental;

  constructor(private rentalService: RentalService) { }

  ngOnInit(): void {}

  onCheckIn()
  {
    this.rentalService.checkInRental(this.rental);
    this.fetchRentalsEmitter.emit(true);
  }
}
