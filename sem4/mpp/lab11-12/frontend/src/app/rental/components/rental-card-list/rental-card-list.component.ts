import {Component, EventEmitter, Input, OnInit} from '@angular/core';
import {Rental} from '../../model/rental';
import {RentalService} from '../../service/rental.service';

@Component({
  selector: 'app-rental-card-list',
  templateUrl: './rental-card-list.component.html',
  styleUrls: ['./rental-card-list.component.css']
})
export class RentalCardListComponent implements OnInit
{
  @Input() fetchRentalsEmitter: EventEmitter<boolean>;
  rentals: Rental[];

  constructor(private rentalService: RentalService)
  {
    this.fetchRenters();
  }

  fetchRenters()
  {
    this.rentalService.getAllRentals().subscribe((rentals: Rental[]) => this.rentals = rentals);
  }

  ngOnInit(): void
  {
    this.fetchRentalsEmitter.subscribe(_ => this.fetchRenters());
  }
}
