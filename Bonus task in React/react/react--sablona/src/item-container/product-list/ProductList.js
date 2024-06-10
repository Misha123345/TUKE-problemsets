import ProductFilter from "./product-filter/ProductFilter";
import './ProductList.css';
import Product from "./product/Product";
import { useState, useContext } from "react";
import SearchContext from "../SearchContext";
import { getProducts } from "../../services/ProductListProvider";


function ProductList(){
  const products = getProducts();

  const { searchQuery } = useContext(SearchContext);
  const [filter, setFilter] = useState('all');
  const [categories, setCategories] = useState({
      "sport": false,
      "casual": false,
      "formal": false,
      "home": false,
      "outdoor": false
  });

  const toggleCategory = (category) => {
    setCategories(prevCategories => ({
        ...prevCategories,
        [category]: !prevCategories[category]
    }));
};

const filteredProducts = products.filter((product) => {
  const categoryFilter = filter === 'all' || product.category === filter;
  const categoryTypes = Object.entries(categories).filter(([key, value]) => value).map(([key]) => key);
  const typesFilter = categoryTypes.length === 0 || categoryTypes.includes(product.type); 
  const searchFilter = !searchQuery || product.name.toLowerCase().includes(searchQuery.toLowerCase());
  return categoryFilter && typesFilter && searchFilter;
});

  return (    
  <>
    <ProductFilter toggleCategory={toggleCategory} categories={categories} setFilter={setFilter}></ProductFilter>
    <div className="product-list">
        {filteredProducts.map((product) => (
          <Product key={products.id} product={product} />
        ))}
    </div>
  </>
  );
}

export default ProductList;