import {Component, EventEmitter, Input, OnInit} from '@angular/core';
import {FilterStrategy} from '../../model/filter-strategy';

@Component({
  selector: 'app-multi-filter',
  templateUrl: './multi-filter.component.html',
  styleUrls: ['./multi-filter.component.css']
})
export class MultiFilterComponent implements OnInit {

  @Input() attributes: string[];
  @Input() operators: object;
  @Input() headerText: string;
  @Input() filterOutput: EventEmitter<FilterStrategy[]>;

  filterEmitters: EventEmitter<FilterStrategy>[] = [
    new EventEmitter<FilterStrategy>(),
    new EventEmitter<FilterStrategy>(),
  ];

  lastFilterOutput: FilterStrategy[] = [
    null,
    null,
  ];

  constructor()
  {
    this.filterEmitters.forEach(emitter => {
      emitter.subscribe((strategy: FilterStrategy) => {
        this.lastFilterOutput[strategy.filterId] = strategy;
        this.filterOutput.emit(this.lastFilterOutput);
      });
    });
  }

  ngOnInit(): void {
  }

}
