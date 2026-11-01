document.querySelectorAll('nav button').forEach(btn=>btn.addEventListener('click',()=>{
 document.querySelectorAll('nav button').forEach(b=>b.classList.remove('active'));
 document.querySelectorAll('.panel').forEach(p=>p.classList.remove('active'));
 btn.classList.add('active');document.getElementById(btn.dataset.tab).classList.add('active');
}));
const picker=document.getElementById('geometryFile');
picker.addEventListener('change',()=>{
 const f=picker.files[0], s=document.getElementById('geometryStatus'), o=document.getElementById('geometryOutput');
 if(!f){s.textContent='No file selected.';return;}
 const ext=f.name.split('.').pop().toLowerCase();
 if(!['stl','csv'].includes(ext)){s.textContent='Unsupported file type.';return;}
 s.textContent=`Selected ${f.name} (${f.size} bytes). C++ validation is required.`;
 o.textContent=ext==='csv'?'Expected header: node_id,x_m,y_m,z_m,temperature_C':'Expected ASCII STL: solid/facet/vertex records.';
});
