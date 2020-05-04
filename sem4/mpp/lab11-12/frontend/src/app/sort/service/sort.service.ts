import { Injectable } from '@angular/core';
import {SortStrategy} from '../model/sort-strategy';

@Injectable({
  providedIn: 'root'
})
export class SortService {

  constructor() { }

  sort(entities, strategy: SortStrategy)
  {
    if (strategy == null) {
      return entities;
    }
    const {attribute, operator} = strategy;
    const sorted = entities.slice();
    sorted.sort((a, b) => a[attribute] < b[attribute] ? -1 : 1);
    if (operator === 'DESC') {
      sorted.reverse();
    }
    return sorted;
  }
}
