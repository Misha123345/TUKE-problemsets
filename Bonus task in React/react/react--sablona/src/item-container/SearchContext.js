import { createContext } from 'react';

const SearchContext = createContext({
  searchQuery: '',
  setSearchQuery: () => {},
});

export default SearchContext;
