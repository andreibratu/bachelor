import { Injectable } from '@angular/core';
import {Observable} from 'rxjs';
import {HttpClient} from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class ReportingService {

  SERVER_ROOT_URL = 'http://localhost:8080';

  constructor(private http: HttpClient) { }

  getTopClients(): Observable<object[]>
  {
    return this.http.get<object[]>(`${this.SERVER_ROOT_URL}/top-clients?limit=3`);
  }

  getBadRenters(): Observable<object[]>
  {
    return this.http.get<object[]>(`${this.SERVER_ROOT_URL}/bad-renters`);
  }

  getRentalsByGenre(): Observable<object[]>
  {
    return this.http.get<object[]>(`${this.SERVER_ROOT_URL}/rentals-genre`);
  }
}
