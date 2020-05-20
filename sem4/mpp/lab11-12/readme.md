# Filtering

* The filter is done on client-side.

* The filter works on AND principle.

* Code related to the filter function can be found in frontend/src/app/filter

* The building block of the filtering is the `filter` component, which is aggregated by the\
  multi-filter component. Calls to the filtering service happen in the client-list and movie-list\
  components. A strategy pattern, found in filter/model/FilterStrategy, is used to coordinate\
  the filtering function.

* The filtering is achieved by having two lists in client-list and movie-list: an actual entity list\
  and a display entity list. The display entity list is presented to the user by appying filtering on
  the entity list. The filtering done by the service is pure, so no alterations happen to the base
  entity list.