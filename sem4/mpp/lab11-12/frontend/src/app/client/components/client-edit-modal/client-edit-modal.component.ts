import {Component, ElementRef, EventEmitter, Input, OnInit, ViewChild} from '@angular/core';
import {Client} from '../../model/client';
import {NgbModal} from '@ng-bootstrap/ng-bootstrap';
import {ClientService} from '../../service/client.service';

@Component({
  selector: 'app-client-edit-modal',
  templateUrl: './client-edit-modal.component.html',
  styleUrls: ['./client-edit-modal.component.css']
})
export class ClientEditModalComponent implements OnInit {
  @Input() editClientOpenModalEmitter: EventEmitter<Client>;
  @ViewChild('content') modal: ElementRef;
  @ViewChild('clientEditForm') form: ElementRef;
  model: Client;

  constructor(private modalService: NgbModal, private clientService: ClientService) { }

  ngOnInit(): void
  {
    this.editClientOpenModalEmitter.subscribe(client => {
      this.model = client;
      this.modalService.open(this.modal).result.then(
        (_) => this.clientService.putClient(this.model).subscribe(() => {}),
        (_) => {}
      );
    });
  }

  onSubmit(form)
  {
    form.reset();
  }

}
