const API_URL = 'http://localhost:8000';

async function listPets()
{
    const response = await fetch(API_URL);
    const pets = await response.json();
    const petList = document.getElementById('pets');
    petList.innerHTML = '';

    pets.forEach(pet =>
    {
        const li = document.createElement('li');
        li.textContent = `${pet}`;
        petList.appendChild(li);
    });
}

window.onload = listPets();

async function getPetDetails()
{
    const petName = document.getElementById('petName').value;
    const response = await fetch(`${API_URL}/${petName}`, {method: 'GET'});

    if (response.ok) 
    {
        const pet = await response.json();
        document.getElementById('details').innerHTML = `
            <p>Name: ${petName}</p>
            <p>Type: ${pet.species}</p>
            <p>Age: ${pet.age}</p>
            <p>Breed: ${pet.breed}</p>
        `;
    } else {
        document.getElementById('details').textContent = 'Pet not found';
    }
}

async function adoptPet()
{
    const adoptName = document.getElementById('adoptName').value;
    
    if (!adoptName)
    {
        alert('Please enter a valid Pet name.');
        return;
    }
        
    const response = await fetch(`${API_URL}/${adoptName}`, {method: 'DELETE'});

    if (response.ok)
    {
        document.getElementById('adoptDetails').textContent = `${adoptName} has been adopted!`;
        listPets();
    } else
    {
        alert('Pet not found. Please check the name and try again.');
    }
    
}

async function updatePet()
{
    console.log("ahhhhhhh");
    const updateName = document.getElementById('updatePetName').value;
    const species = document.getElementById('species').value;
    const age = document.getElementById('age').value;
    const breed = document.getElementById('breed').value;


    const petData = { species, breed, age };

    try {
        const response = await fetch(`${API_URL}/${updateName}`, {
            method: 'PATCH',
            body: JSON.stringify(petData)
        });

        const responseText = await response.text();

        if (response.ok) 
        {
            document.getElementById("updateDetails").textContent = `${updateName} has been updated.`
            listPets();
        } else {
            alert('Failed to update pet: ' + responseText);
        }
    } catch (error) {
        console.error('Error updating pet:', error);
        alert('An error occurred while updating the pet');
    }

}

async function addPet()
{
    const name = document.getElementById('nameAdd').value;
    const species = document.getElementById('speciesAdd').value;
    const age = document.getElementById('ageAdd').value;
    const breed = document.getElementById('breedAdd').value;

    const petData = { species, breed, age };
    const response = await fetch(`${API_URL}/${name}`, 
        {
            method: 'POST',
            body: JSON.stringify(petData)
        }
    );

    if (response.ok)
    {
        document.getElementById("addDetails").textContent = `${name} has been added.`;
        listPets();
    }
}