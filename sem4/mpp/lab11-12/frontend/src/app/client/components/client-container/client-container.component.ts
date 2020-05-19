import {Component, EventEmitter, OnInit} from '@angular/core';
import {Client} from '../../model/client';
import {FilterStrategy} from '../../../filter/model/filter-strategy';
import {SortStrategy} from '../../../sort/model/sort-strategy';

@Component({
  selector: 'app-client-container',
  templateUrl: './client-container.component.html',
  styleUrls: ['./client-container.component.css']
})
export class ClientContainerComponent implements OnInit {

  newClientEmitter: EventEmitter<Client>;
  editClientOpenModalEmitter: EventEmitter<Client>;
  clientFilterEmitter: EventEmitter<FilterStrategy[]>;
  clientSortEmitter: EventEmitter<SortStrategy>;

  constructor()
  {
    this.newClientEmitter = new EventEmitter<Client>();
    this.editClientOpenModalEmitter = new EventEmitter<Client>();
    this.clientFilterEmitter = new EventEmitter<FilterStrategy[]>();
    this.clientSortEmitter = new EventEmitter<SortStrategy>();
  }

  ngOnInit(): void {
  }

}
