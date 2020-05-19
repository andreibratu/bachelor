import {Component, Input, OnInit} from '@angular/core';
import {Observable} from 'rxjs';

@Component({
  selector: 'app-reporting-card',
  templateUrl: './reporting-card.component.html',
  styleUrls: ['./reporting-card.component.css']
})
export class ReportingCardComponent implements OnInit {

  @Input() reportTitle: string;
  @Input() report: Observable<any>;
  @Input() callback: (object) => string;
  reportText: string;

  constructor() {
    this.reportText = '';
  }

  ngOnInit(): void {
    this.report.subscribe((result: object[]) => {
      console.log(result);
      this.reportText = result.length !== 0 ?
        result.reduce((acc, currObj) => {
          return acc + this.callback(currObj);
        }, '') :
        'Nothing to report!';
    });
  }
}
