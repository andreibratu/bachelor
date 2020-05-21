import {Component, EventEmitter, Input, OnInit} from '@angular/core';
import {Client} from '../../model/client';
import {ClientService} from '../../service/client.service';
import {FilterStrategy} from '../../../filter/model/filter-strategy';
import {FilterService} from '../../../filter/service/filter.service';
import {SortStrategy} from '../../../sort/model/sort-strategy';
import {SortService} from '../../../sort/service/sort.service';

@Component({
  selector: 'app-client-card-list',
  templateUrl: './client-card-list.component.html',
  styleUrls: ['./client-card-list.component.css']
})
export class ClientCardListComponent implements OnInit
{
  clients: Client[];
  clientsDisplay: Client[];
  sortStrategy: SortStrategy = null;
  deleteClientEmitter: EventEmitter<number>;
  @Input() newClientEmitter: EventEmitter<Client>;
  @Input() editClientOpenModalEmitter: EventEmitter<Client>;
  @Input() clientFilterEmitter: EventEmitter<FilterStrategy[]>;
  @Input() clientSortEmitter: EventEmitter<SortStrategy>;

  constructor(
    private clientService: ClientService,
    private filterService: FilterService,
    private sortService: SortService
  )
  {
    this.clients = [];
    this.deleteClientEmitter = new EventEmitter<number>();
  }

  ngOnInit(): void
  {
    this.clientService.getAllClients().subscribe((response: Client[]) => {
      this.clients = response;
      this.clientsDisplay = this.clients.slice();
    });
    this.newClientEmitter.subscribe(client => {
      this.clients.push(client);
      this.clientsDisplay = this.clients.slice();
    });
    this.deleteClientEmitter.subscribe(id => {
      this.clientService.deleteClient(id).subscribe(_ => {
        this.clients = this.clients.filter(client => client.id !== id);
        this.clientsDisplay = this.clients.slice();
      });
    });
    this.clientFilterEmitter.subscribe((strategies: FilterStrategy[]) => {
      this.clientsDisplay = this.filterService.multipleFilter(this.clients, strategies);
      // Re-apply sorting strategy on the new filtered list.
      this.clientsDisplay = this.sortService.sort(this.clientsDisplay, this.sortStrategy);
    });
    this.clientSortEmitter.subscribe((strategy) => {
      this.clientsDisplay = this.sortService.sort(this.clientsDisplay, strategy);
      // Keep the strategy throughout modifications in the filtering
      this.sortStrategy = strategy;
    });
  }
}
