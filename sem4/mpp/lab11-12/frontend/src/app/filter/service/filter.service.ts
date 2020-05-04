import { Injectable } from '@angular/core';
import {FilterStrategy} from '../model/filter-strategy';

@Injectable({
  providedIn: 'root'
})
export class FilterService {

  constructor() { }

  filter(entities, strategy: FilterStrategy)
  {
    if (strategy == null) { return entities; }
    // tslint:disable-next-line:prefer-const
    let {attribute, operator, value} = strategy;
    value = value.toLowerCase();
    if (!['EQ', 'NEQ', 'CONTAINS'].includes(operator))
    {
      // Value is to be treated as a number
      // @ts-ignore
      if (isNaN(value)) { return entities; }
      // @ts-ignore
      value = parseFloat(value);
    }
    let filtered = entities.slice();
    switch (operator)
    {
      // String ops
      case 'CONTAINS':
        filtered = filtered.filter(entity => entity[attribute].toLowerCase().includes(value));
        break;
      case 'NEQ':
        console.log('NEQ');
        filtered = filtered.filter(entity => entity[attribute].toLowerCase() !== value);
        break;
      case 'EQ':
        console.log('EQ');
        filtered = filtered.filter(entity => entity[attribute].toLowerCase() === value);
        break;
      // Number ops
      case '==':
        filtered = filtered.filter(entity => entity[attribute].toLowerCase() === value);
        break;
      case '!=':
        filtered = filtered.filter(entity => entity[attribute].toLowerCase() !== value);
        break;
      case '>':
        filtered = filtered.filter(entity => entity[attribute].toLowerCase() > value);
        break;
      case '<':
        filtered = filtered.filter(entity => entity[attribute].toLowerCase() < value);
        break;
    }
    console.log(filtered);
    return filtered;
  }
}
