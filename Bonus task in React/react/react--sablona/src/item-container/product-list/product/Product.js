import './Product.css'

function Product({product}){

    const inventoryStatusStyle = {
        color: product.is_in_inventory ? 'green' : 'red',
        fontWeight: 'bold'
    };

    return (
        <>
            <div className="product-container">

            {product.discountPrice && (
                <div className="product-sale-bubble" >{(100-(product.discountPrice / product.price *100)).toFixed(0)}% OFF</div>
                )}
            
                <div className="product-image">
                    <img src= {product.imageURL} alt="halabala"  className="product-image" />
                </div>

                <div className="product-price">{ product.price }</div>

                <div className="product-brand">{ product.brand }</div>

                <div className="product-name">{ product.name }</div>

                <div className="product-info-text">{ product.type } . { product.category } . { product.length } colors </div>

                <div style= {inventoryStatusStyle} className="product-info-text" >{product.is_in_inventory ? 'Produkt je na sklade' : 'Produkt nie je na sklade'}</div>
            </div>
        </>
    );
}

export default Product;