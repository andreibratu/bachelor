import {Component, EventEmitter, Input, OnInit} from '@angular/core';
import {SortStrategy} from '../model/sort-strategy';

@Component({
  selector: 'app-sort',
  templateUrl: './sort.component.html',
  styleUrls: ['./sort.component.css']
})
export class SortComponent implements OnInit
{
  @Input() attributes: string[];
  @Input() entitySortEmitter: EventEmitter<SortStrategy>;
  operators = ['-', 'ASC', 'DESC'];
  selectedAttribute: string;
  selectedOperator = '-';

  constructor() { }

  ngOnInit(): void
  {
    this.selectedAttribute = this.attributes[0];
  }

  toAttributeCase(str: string)
  {
    // Lowercase the first letter of the attribute name, leaving all other uppercases as they are
    return str.charAt(0).toLowerCase() + str.slice(1);
  }

  onSelectAttribute(attributeSelectRef)
  {
    console.log('ATTR AAAA');
    this.selectedAttribute = this.toAttributeCase(attributeSelectRef.value);
    this.emitStrategy();
  }

  onSelectOperator(operatorSelectRef)
  {
    console.log('OPERATOR AAAA');
    this.selectedOperator = operatorSelectRef.value;
    this.emitStrategy();
  }

  emitStrategy()
  {
    let strategy: SortStrategy = null;
    if (this.selectedOperator !== '-')
    {
      strategy = {
        attribute: this.selectedAttribute,
        operator: this.selectedOperator
      };
    }
    this.entitySortEmitter.emit(strategy);
  }
}
