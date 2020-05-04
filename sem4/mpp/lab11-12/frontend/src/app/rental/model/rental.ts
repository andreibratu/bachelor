import {Client} from '../../client/model/client';
import {Movie} from '../../movie/model/movie/movie';

export class Rental
{
  constructor(
    public id: number | null,
    public client: Client,
    public movie: Movie,
    public startDate: Date,
    public endDate: Date | null
  ) {
  }
}
