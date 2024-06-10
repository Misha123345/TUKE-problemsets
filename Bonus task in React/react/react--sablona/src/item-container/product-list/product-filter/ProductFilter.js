import './ProductFilter.css';

function MyButton({categories, type, toggleCategory, children}) {
    return <button onClick={() => toggleCategory(type)} className={categories[type] ? "custom-button active" : "custom-button"}>{children}</button>
}

function ProductFilter({toggleCategory, categories, setFilter}){
    return(  
    <>
        <div className="filter-container">
            <input 
                type="radio" 
                name="filter" 
                value="all"
                onClick={() => setFilter("all")}
            />
            <span>Všetko</span>
            
            <input 
                type="radio" 
                name="filter" 
                value="men"
                onClick={() => setFilter("men")}
            />
            <span>Pánska obuv</span>

            <input 
                type="radio" 
                name="filter" 
                value="women" 
                onClick={() => setFilter("women")}
            />
            <span>Dámska obuv</span>

            <input 
                type="radio" 
                name="filter" 
                value="kids" 
                onClick={() => setFilter("kids")}
            />
        <span>Detská obuv</span>
        </div>

        <div className="category-container">
            <MyButton categories={categories} type="sport" toggleCategory={toggleCategory}>Tenisky</MyButton>
            <MyButton categories={categories} type="casual" toggleCategory={toggleCategory}>Komfortná obuv</MyButton>
            <MyButton categories={categories} type="formal" toggleCategory={toggleCategory}>Formálna obuv</MyButton>
            <MyButton categories={categories} type="home" toggleCategory={toggleCategory}>Obuv na doma</MyButton>
            <MyButton categories={categories} type="outdoor" toggleCategory={toggleCategory}>Outdoorová obuv</MyButton>
        </div>

    </> 
    );
}

export default ProductFilter;