


const products= [
    {
      id: 1,
      name: "Buggati Denim Trevor",
      brand: "BUGATTI DENIM",
      type: "sport",
      category: "men",
      color: ["White", "Blue", "Black"],
      price: 94,
      is_in_inventory: true,
      imageURL: "https://www.humanic.net/images/productimages/2221148608_1_pdp_gallery.jpg"
    },
    {
      id: 2,
      name: "Puma Caven CVS",
      brand: "PUMA",
      type: "sport",
      category: "men",
      color: ["White", "Blue", "Black"],
      price: 69,
      discountPrice:45,
      is_in_inventory: false,
      imageURL: "https://www.humanic.net/images/productimages/2731111470_1_pdp_gallery.jpg"
    },
    {
      id: 3,
      name: "Puma Cali Dream",
      brand: "PUMA",
      type: "sport",
      category: "women",
      color: ["White", "Blue", "Black"],
      price: 99,
      is_in_inventory: true,
      imageURL: "https://www.humanic.net/images/productimages/1711151705_1_pdp_gallery.jpg"
    },
    {
      id: 4,
      name: "Puma Cassia Laser Cut",
      brand: "PUMA",
      type: "sport",
      category: "women",
      color: ["White", "Blue", "Black"],
      price: 79,
      discountPrice:29,
      is_in_inventory: true,
      imageURL: "https://www.humanic.net/images/productimages/1711148205_1_pdp_gallery.jpg"
    },
    {
      id: 5,
      name: "Superfit JUPITER",
      brand: "SUPERFIT",
      type: "sport",
      category: "kids",
      color: ["White", "Blue", "Black"],
      price: 84,
      is_in_inventory: true,
      imageURL: "https://www.humanic.net/images/productimages/4221212038_1_pdp_gallery.jpg"
    },
    {
      id: 6,
      name: "Josef Seibel Anvers 81",
      brand: "JOSEF SEIBEL",
      type: "casual",
      category: "men",
      color: ["White", "Blue", "Black"],
      price: 79,
      discountPrice:64,
      is_in_inventory: true,
      imageURL: "https://www.humanic.net/images/productimages/2401203844_1_plp_thumbnail.jpg"
    },
    {
      id: 7,
      name: "Buggate Denim Arriba",
      brand: "BUGATTI DENIM",
      type: "casual",
      category: "men",
      color: ["White", "Blue", "Black"],
      price: 59,
      is_in_inventory: false,
      imageURL: "https://www.humanic.net/images/productimages/2221205930_1_plp_thumbnail.jpg"
    },
    {
      id: 8,
      name: "Pat Calvin",
      brand: "PAT CALVIN",
      type: "casual",
      category: "women",
      color: ["White", "Blue", "Black"],
      price: 109,
      is_in_inventory: true,
      imageURL: "https://www.humanic.net/images/productimages/1221216408_1_plp_thumbnail.jpg"
    },
    {
      id: 9,
      name: "Rieker Slipper",
      brand: "RIEKER",
      type: "casual",
      category: "women",
      color: ["White", "Blue", "Black"],
      price: 69,
      discountPrice:50,
      is_in_inventory: true,
      imageURL: "https://www.humanic.net/images/productimages/1401201517_1_plp_thumbnail.jpg"
    },
    {
      id: 10,
      name: "Superfit Freddy",
      brand: "SUPERFIT",
      type: "casual",
      category: "kids",
      color: ["White", "Blue", "Black"],
      price: 69,
      discountPrice:39,
      is_in_inventory: true,
      imageURL: "https://www.humanic.net/images/productimages/4623507636_1_plp_thumbnail.jpg"
    },
    {
      id: 11,
      name: "Lazzarini",
      brand: "LAZZARINI",
      type: "formal",
      category: "men",
      color: ["White", "Blue", "Black"],
      price: 99,
      discountPrice: 45,
      is_in_inventory: true,
      imageURL: "https://www.humanic.net/images/productimages/2121138499_1_plp_thumbnail.jpg"
    },
    {
      id: 12,
      name: "Buggatti Mattia",
      brand: "BUGATTI",
      type: "formal",
      category: "men",
      color: ["White", "Blue", "Black"],
      price: 79,
      is_in_inventory: true,
      imageURL: "https://www.humanic.net/images/productimages/2111110310_1_plp_thumbnail.jpg"
    },
    {
      id: 13,
      name: "Graz Highsoft",
      brand: "ARA",
      type: "formal",
      category: "women",
      color: ["White", "Blue", "Black"],
      price: 109,
      is_in_inventory: true,
      imageURL: "https://www.humanic.net/images/productimages/1181411766_1_plp_thumbnail.jpg"
    },
    {
      id: 14,
      name: "Graz 2.0",
      brand: "ARA",
      type: "formal",
      category: "women",
      color: ["White", "Blue", "Black"],
      price: 119,
      is_in_inventory: false,
      imageURL: "https://www.humanic.net/images/productimages/1181411700_1_plp_thumbnail.jpg"
    },
    {
      id: 15,
      name: "Small Gentleman",
      brand: "IDK",
      type: "formal",
      category: "kids",
      color: ["White", "Blue", "Black"],
      price: 60,
      discountPrice: 25,
      is_in_inventory: true,
      imageURL: "https://m.media-amazon.com/images/I/41PitNS6v0L._AC_SY780_.jpg"
    },
    {
      id: 16,
      name: "Salomon Wander GTX",
      brand: "SALOMON",
      type: "outdoor",
      category: "men",
      color: ["White", "Blue", "Black"],
      price: 109,
      is_in_inventory: true,
      imageURL: "https://www.humanic.net/images/productimages/2719506399_1_plp_thumbnail.jpg"
    },
    {
      id: 17,
      name: "Salomon Eletra Low WP",
      brand: "SALOMON",
      type: "outdoor",
      category: "men",
      color: ["White", "Blue", "Black"],
      price: 99,
      is_in_inventory: true,
      imageURL: "https://www.humanic.net/images/productimages/2809501808_1_plp_thumbnail.jpg"
    },
    {
      id: 18,
      name: "Salomon Wander GtX W",
      brand: "SALOMON",
      type: "outdoor",
      category: "women",
      color: ["White", "Blue", "Black"],
      price: 109,
      is_in_inventory: true,
      imageURL: "https://www.humanic.net/images/productimages/1719503870_1_plp_thumbnail.jpg"
    },
    {
      id: 19,
      name: "Salomon Alphacross 5 GTX W",
      brand: "SALOMON",
      type: "outdoor",
      category: "women",
      color: ["White", "Blue", "Black"],
      price: 129,
      is_in_inventory: false,
      imageURL: "https://www.humanic.net/images/productimages/1719503840_1_plp_thumbnail.jpg"
    },
    {
      id: 20,
      name: "Salomon Patrol J",
      brand: "SALOMON",
      type: "outdoor",
      category: "kids",
      color: ["White", "Blue", "Black"],
      price: 50,
      discountPrice: 25,
      is_in_inventory: true,
      imageURL: "https://www.humanic.net/images/productimages/4711110204_1_plp_thumbnail.jpg"
    },
    {
      id: 21,
      name: "Natura pantofle",
      brand: "NATURA",
      type: "home",
      category: "men",
      color: ["White", "Blue", "Black"],
      price: 20,
      discountPrice: 12,
      is_in_inventory: true,
      imageURL: "https://www.humanic.net/images/productimages/2802600770_1_plp_thumbnail.jpg"
    },
    {
      id: 22,
      name: "Birkenstock Arizona",
      brand: "BIRKENSTOCK",
      type: "home",
      category: "men",
      color: ["White", "Blue", "Black"],
      price: 84 ,
      is_in_inventory: true,
      imageURL: "https://www.humanic.net/images/productimages/2802602782_1_plp_thumbnail.jpg"
    },
    {
      id: 23,
      name: "Natura papuče",
      brand: "NATURA",
      type: "home",
      category: "women",
      color: ["White", "Blue", "Black"],
      price: 19,
      discountPrice: 9,
      is_in_inventory: false,
      imageURL: "https://www.humanic.net/images/productimages/1872004177_1_plp_thumbnail.jpg"
    },
    {
      id: 24,
      name: "Natura Sakura",
      brand: "NATURA",
      type: "home",
      category: "women",
      color: ["White", "Blue", "Black"],
      price: 12,
      is_in_inventory: false,
      imageURL: "https://www.humanic.net/images/productimages/1802606998_1_plp_thumbnail.jpg"
    },
    {
      id: 25,
      name: "Superfit Sparkle",
      brand: "SUPERFIT",
      type: "home",
      category: "kids",
      color: ["White", "Blue", "Black"],
      price: 12,
      is_in_inventory: true,
      imageURL: "https://www.humanic.net/images/productimages/3802602598_1_plp_thumbnail.jpg"
    }
  ];

  export function getProducts(){
    return products;
  }