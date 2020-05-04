import {Component, EventEmitter, Input, OnInit} from '@angular/core';
import {Client} from '../../model/client';

@Component({
  selector: 'app-client-card',
  templateUrl: './client-card.component.html',
  styleUrls: ['./client-card.component.css']
})
export class ClientCardComponent implements OnInit
{
  @Input() client: Client;
  @Input() deleteClientHandler: EventEmitter<number>;
  @Input() editClientOpenModalHandler: EventEmitter<Client>;

  constructor() { }

  ngOnInit(): void {}

  onDelete()
  {
    this.deleteClientHandler.emit(this.client.id);
  }

  onEdit()
  {
    this.editClientOpenModalHandler.emit(this.client);
  }
}
