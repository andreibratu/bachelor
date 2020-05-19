import { Component, OnInit } from '@angular/core';
import {ReportingService} from '../../service/reporting.service';

@Component({
  selector: 'app-reporting-container',
  templateUrl: './reporting-container.component.html',
  styleUrls: ['./reporting-container.component.css']
})
export class ReportingContainerComponent implements OnInit {

  topClientsCallback: (object) => string = (obj) => `${obj.key.name}: ${obj.value}\n`;
  badRentersCallback: (object) => string = (obj) => `${obj.name}\n`;
  rentalsGenreCallback: (object) => string = (obj) => `${obj.key}: ${obj.value}\n`;

  constructor(public reportingService: ReportingService) { }

  ngOnInit(): void {
  }

}
