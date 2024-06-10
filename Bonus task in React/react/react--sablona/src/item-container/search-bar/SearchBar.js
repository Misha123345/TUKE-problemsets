import { useContext} from 'react';
import './SearchBar.css'
import SearchContext from '../SearchContext';

function SearchBar(){
    const { searchQuery, setSearchQuery } = useContext(SearchContext);

    return(
        <div class="search-bar-container">
            <input class="search-bar-input" value={searchQuery} onChange={e => setSearchQuery(e.target.value)}/>
            <button class="button">Hľadaj</button>
        </div>
    );
}

export default SearchBar;