import {Injectable} from '@angular/core';
import {Client} from '../model/client';
import {HttpClient, HttpHeaders} from '@angular/common/http';
import {Observable} from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class ClientService
{
  SERVER_URL = 'http://localhost:8080/clients';

  constructor(private http: HttpClient) {}

  getAllClients(): Observable<object>
  {
    return this.http.get<Client[]>(this.SERVER_URL);
  }

  createClient(client: Client): Observable<object>
  {
    return this.http.post(this.SERVER_URL, {name: client.name, address: client.address});
  }

  deleteClient(id: number): Observable<object>
  {
    return this.http.delete(this.SERVER_URL + `/${id}`);
  }

  putClient(client: Client): Observable<object>
  {
    return this.http.put(this.SERVER_URL + `/${client.id}`, client);
  }
}
