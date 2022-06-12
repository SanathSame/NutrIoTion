import streamlit as st
from google.cloud import firestore
import pandas as pd
from time import sleep

# Authenticate to Firestore with the JSON account key.
db = firestore.Client.from_service_account_json("firebase-key.json")

# Create a reference to the Google post.
doc_ref = db.collection("values").document("MQ3 sensor")

# Then get the data at that reference.
doc = doc_ref.get()


st.title("NutrIoTion")
st.header("Read gas sensor values")
choices_name = st.selectbox("View results from", ("Crate Number 1", "Crate Number 2", "Crate Number 3"))
st.write(choices_name)
st.header('Stream of gas sensor values')
data = pd.read_csv('HardCode_Data.csv')
chart_data = data.loc[:, data.columns != ('Timestamp')]
st.line_chart(chart_data)

col1, col2 = st.columns(2)
with col1:
    st.header("Rotten Apple displayed by image sensors")
    image = Image.open('badapple.jpg')
    st.image(image)
with col2:
    st.header("Fresh apple displayed by image sensors")
    image1 = Image.open('freshapple.jpg')
    st.image(image1)

st.subheader('Deduction for batch of perishables for three hour slot')

st.metric(label="Gas value", value=4, delta=-0.5,
     delta_color="inverse")

st.metric(label="Image analysis", value= "Fresh", delta = 1,
     delta_color="normal")


