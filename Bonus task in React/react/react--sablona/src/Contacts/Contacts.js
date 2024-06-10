import React from "react"
import { Link } from "react-router-dom"
import "./Contacts.css"

const Contacts = () => {
  return (
    <div className="contacts">
      <h1>Contacts</h1>
      <button><Link to={"/item-container"}>Item Container</Link></button>
    </div> 
  )
}

export default Contacts