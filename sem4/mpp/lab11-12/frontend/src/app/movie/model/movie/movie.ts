import {Genre} from '../genre/genre.enum';

export class Movie
{
  constructor(
    public id: number | null,
    public title: string,
    public year: number,
    public genre: Genre
  ) {
  }
}
