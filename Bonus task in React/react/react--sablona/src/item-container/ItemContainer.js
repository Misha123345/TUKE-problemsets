import ProductList from "./product-list/ProductList";
import './ItemContainer.css'
import SearchBar from "./search-bar/SearchBar";

function ItemContainer() {
    return(
    <>
        <SearchBar></SearchBar>
            <div class="item-container">
            <ProductList></ProductList>
        </div>
    </>
    );
}

export default ItemContainer;