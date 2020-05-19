import {Component, EventEmitter, Input, OnInit} from '@angular/core';
import {FilterStrategy} from '../../model/filter-strategy';

@Component({
  selector: 'app-filter',
  templateUrl: './filter.component.html',
  styleUrls: ['./filter.component.css']
})
export class FilterComponent implements OnInit
{
  @Input() attributes: string[];
  @Input() operators: object;
  @Input() entityFilterEmitter: EventEmitter<FilterStrategy>;
  @Input() filterId: number;
  selectedValue = '';
  selectedAttribute: string;
  selectedOperator: string;
  attributeOperators: string[];

  constructor() {}

  ngOnInit(): void
  {
    this.selectedAttribute = this.attributes[0];
    this.attributeOperators = this.operators[this.selectedAttribute];
    this.selectedOperator = this.attributeOperators[0];
  }

  onSelectAttribute(selectRef)
  {
    this.selectedAttribute = this.toAttributeCase(selectRef.value);
    this.attributeOperators = this.operators[this.selectedAttribute];
    this.selectedOperator = this.attributeOperators[0];
    this.selectedValue = '';
  }

  toAttributeCase(str: string)
  {
    /*
      Lowercase the first letter of the attribute name,
      leaving all other uppercase letters as they are
    */
    return str.charAt(0).toLowerCase() + str.slice(1);
  }

  onValueInput()
  {
    if (this.selectedValue === '')
    {
      this.entityFilterEmitter.emit(null);
    }
    else
    {
      console.log(this.selectedAttribute, this.selectedOperator, this.selectedValue);
      this.entityFilterEmitter.emit({
        attribute: this.toAttributeCase(this.selectedAttribute),
        operator: this.selectedOperator,
        value: this.selectedValue,
        filterId: this.filterId
      });
    }
  }
}
