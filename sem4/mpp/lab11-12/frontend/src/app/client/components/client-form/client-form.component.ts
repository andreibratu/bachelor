import {Component, EventEmitter, Input, OnInit} from '@angular/core';
import {Client} from '../../model/client';
import {ClientService} from '../../service/client.service';

@Component({
  selector: 'app-client-form',
  templateUrl: './client-form.component.html',
  styleUrls: ['./client-form.component.css']
})
export class ClientFormComponent implements OnInit
{
  model: Client = this.emptyClient();
  @Input() newClientEmitter: EventEmitter<Client>;

  constructor(private clientService: ClientService) {}

  ngOnInit(): void {}

  emptyClient(): Client
  {
    return new Client(null, '', '');
  }

  onSubmit(form)
  {
    this.clientService.createClient(this.model).subscribe((client: Client) => {
      this.newClientEmitter.emit(client);
    });
    this.model = this.emptyClient();
    form.reset();
  }
}
